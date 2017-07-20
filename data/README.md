This directory holds sample data files to use for analysis.

The `clear` subdirectory holds copies of data files which show
exceptionally clear streamers.

#### Naming convention
- A file name has a "prefix" and a "kind"
- The prefix and kind are separated by a `-` character
- The kind can have two values:
    - `s`: means that this image was simulated
    - `o`: means that this image was observed
- Files with the same prefix belong to the same date, time, and carrington rotation
- `prefix_lookup.csv` can be used to find the date, time, and carrington rotation of each prefix


#### Additional files
- `streamer-angles.csv` contains all the identified angles in each file.
  Angles are in radians and are measured from the left horizontal axis up
- `correlation.csv` contains the difference in angle between correlated streamers **(simulated - observed)**
- `stats.txt` contains statistics on the values found in `correlation.csv`
