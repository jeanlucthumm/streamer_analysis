**The following is outdated. Currently, only `diff_stats.py` is used**


**process_correlations.py** is the script used to output the `correlations.csv` file. It reads in an angle file
and tries to find correlated streamers, for which it computes the delta or difference (simulated - observed). Usage
is as follows:

    USAGE: process_correlation angles_file out_file thresh
      angles_file: csv file containing streamer angles for indiv images
      out_file: where to write correlation deltas in csv format
      thresh: all deltas are under this value are considered a correlation
      

**analyze_correlations.py** reads in a correlation file outputed by *process_correlations.py* and outputs statistics
on the diff values. Usage is as follows:

    USAGE: analyze_correlations input [output]
      input: csv file containing correlation delta for each prefix
      output: optional output file to output stats to
