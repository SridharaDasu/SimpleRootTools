# SimpleRootTools

Example usage to create a root file from an ASCII file with white space separated data:

```bash
root -q -l readASCIINTuple\('"file.dat"'\)
```

The first row of input file is expected to contain white space separated variable names.

Example usage to create png plot dump of all leaves of all trees in a root file:

```bash
root -q -l dumpPlots.C\('"JetAnalyzer-DYJetsToLL.root"'\)
```

Example usage to create png plot comparison of all leaves of all trees in root file:

```bash
root -q -l comparisonPlots.C\('"JetAnalyzer-DYJetsToLL.root"','"JetAnalyzer-WprimeToTauNu.root"'\)
```

For comparisonPlots.C both root files should have the same structure, same trees and same variables.

Above scripts assume that there are no subdirectories.  It should be easy to generalize the case.
If you help clean that part up, please feel free to make a pull request.
