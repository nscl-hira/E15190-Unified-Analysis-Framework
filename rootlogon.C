{
  gROOT->ProcessLine(".L lib/libE15190Reader.so");
  gROOT->ProcessLine(".L lib/libHTRunInfo.so");

  gROOT->ProcessLine(".L HTRunInfo/HTRunInfo.cxx");
  gROOT->ProcessLine(".L HTRunInfo/HTExperimentInfo.cxx");
  gROOT->ProcessLine(".L HTRunInfo/HTDAQStackInfo.cxx");
  gROOT->ProcessLine(".L HTRunInfo/HTModuleInfo.cxx");
}
