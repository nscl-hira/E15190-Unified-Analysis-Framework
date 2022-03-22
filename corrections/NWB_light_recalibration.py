import warnings

from sympy import Line
warnings.filterwarnings('ignore')

import numpy as np
import pandas as pd
from scipy.optimize import curve_fit

# read in the old (current) calibration as df_old
path = '../calibrations/NWB_PulseHeightCalibration.dat'
df_old = pd.read_csv(path, sep='\t', skiprows=1, header=None).loc[:, :5]
df_old.columns = ['bar', 'a', 'b', 'c', 'd', 'e']
df_old['bar'] = df_old['bar'].str.extract('(\d+)', expand=False).astype(int)
df_old.set_index('bar', inplace=True)

# functions to fit
# https://github.com/nscl-hira/E15190-Unified-Analysis-Framework/blob/4521b84863cf8d56124e30f2e9ef2a0627e11711/NWPulseHeightCalibration.cpp
def get_light(chn, x, a, b, c, d, e):
    result = chn / (a + b * x + c * x ** 2)
    result = d + result * (4.916 * e)
    return result

def get_adc(light, x, a, b, c, d, e):
    result = (light - d) / (4.916 * e)
    result = result * (a + b * x + c * x ** 2)
    return result

# updated the calibration points (MeVee)
# using Geant4 simulation, with the correct NW bar dimensions
old_calib_lights = {
    'pedestal': 0.0, 'AmBe': 4.44,
    '90 deg': 11.02, '44.4 deg': 15.6538, '56.3 deg': 20.3242,
}
new_calib_lights = {
    'pedestal': 0.0, 'AmBe': 4.44,
    '90 deg': 11.96, '44.4 deg': 17.0536, '56.3 deg': 22.1550,
}

# a draw routine for every bar
def routine(bar, ax):
    global df_old
    df_bar = df_old.loc[bar]
    old_data = pd.DataFrame(
        [
            [old_calib_lights['pedestal'], 0.0],
            [old_calib_lights['AmBe'], get_adc(old_calib_lights['AmBe'], 0, *df_bar)],
            [old_calib_lights['90 deg'], get_adc(old_calib_lights['90 deg'], 0, *df_bar)],
            [old_calib_lights['44.4 deg'], get_adc(old_calib_lights['44.4 deg'], 0, *df_bar)],
            [old_calib_lights['56.3 deg'], get_adc(old_calib_lights['56.3 deg'], 0, *df_bar)],
        ],
        columns=['light', 'adc'],
    )
    old_data.index = list(old_calib_lights.keys())

    new_data = pd.DataFrame(
        [
            [new_calib_lights['pedestal'], 0.0],
            [new_calib_lights['AmBe'], old_data.loc['AmBe', 'adc']],
            [new_calib_lights['90 deg'], old_data.loc['90 deg', 'adc']],
            [new_calib_lights['44.4 deg'], old_data.loc['44.4 deg', 'adc']],
            [new_calib_lights['56.3 deg'], old_data.loc['56.3 deg', 'adc']],
        ],
        columns=['light', 'adc'],
    )
    new_data.index = list(new_calib_lights.keys())

    par = curve_fit(
        lambda light, *args: get_adc(light, 0, *args),
        new_data['light'], new_data['adc'],
        p0=tuple(df_bar),
        bounds=(
            (df_bar.a - 3, df_bar.b - 0.05, df_bar.c - 0.05, df_bar.d - 0.1, df_bar.e - 0.1),
            (df_bar.a + 3, df_bar.b + 0.05, df_bar.c + 0.05, df_bar.d + 0.1, df_bar.e + 0.1),
        )
    )[0]

    light = np.linspace(-1, 100, 200) # MeVee
    ax.plot(light, get_adc(light, 0, *df_bar), color='black', linewidth=0.3)
    ax.plot(light, get_adc(light, -100, *df_bar), color='gray', linewidth=0.3, linestyle='dashed')
    ax.plot(light, get_adc(light, 100, *df_bar), color='gray', linewidth=0.3, linestyle='dashed')
    ax.plot(light, get_adc(light, 0, *par), color='red', linewidth=0.3)
    ax.plot(light, get_adc(light, -100, *par), color='pink', linewidth=0.3, linestyle='dashed')
    ax.plot(light, get_adc(light, 100, *par), color='pink', linewidth=0.3, linestyle='dashed')
    ax.errorbar(old_data['light'], old_data['adc'], label='old', fmt='s', markersize=1, zorder=100, color='black')
    ax.errorbar(new_data['light'], new_data['adc'], label='new', fmt='s', markersize=1, zorder=100, color='red')
    return par


# draw summary plot
import matplotlib as mpl
import matplotlib.pyplot as plt
mpl.rcParams.update({
    'font.family': 'serif',
    'xtick.top': True,
    'xtick.direction': 'in',
    'xtick.minor.visible': True,
    'ytick.right': True,
    'ytick.direction': 'in',
    'ytick.minor.visible': True,
})

fig, ax = plt.subplots(ncols=6, nrows=4, figsize=(12, 9), dpi=300, constrained_layout=True, facecolor='white')
df_new = []
for bar in range(1, 25):
    rc = (int((bar - 1) / 6), (bar - 1) % 6)
    ax[rc].set_title(f'bar-{bar:02d}')
    # ax[rc].set_xlim(-1, 25)
    # ax[rc].set_ylim(-100, 1600)
    ax[rc].set_xlim(-1, 80)
    ax[rc].set_ylim(-100, 4100)
    ax[rc].set_xticks([0, 20, 40, 60, 80])
    ax[rc].set_yticks([0, 1000, 2000, 3000, 4000])
    ax[rc].grid(linestyle='dashed', linewidth=0.1, color='gray', zorder=1)
    par = routine(bar, ax[rc])
    df_new.append(par)
    if rc[0] == 3:
        ax[rc].set_xlabel('Light (MeVee)')
    else:
        ax[rc].set_xticklabels([])
    if rc[1] == 0:
        ax[rc].set_ylabel('GeoMean ADC')
    else:
        ax[rc].set_yticklabels([])
ax[0, 0].legend(loc='upper left', handletextpad=0.05)
plt.savefig('output.png', dpi=600, bbox_inches='tight')
plt.draw()
# plt.show()

df_new = pd.DataFrame(df_new, columns=['a', 'b', 'c', 'd', 'e'])
df_new.insert(0, '*numbar', [f'NWBbar{bar:02d}' for bar in range(1, 25)])
try:
    from e15190.utilities import tables
    tables.to_fwf(df_new, 'output.dat')
except ImportError:
    df_new.to_csv('output.csv', index=False, sep='\t')

print('Done')