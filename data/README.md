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


#### Analysis Files
These files contain analysis done on the data set, and can be found in the `analysis` subdirectory.
- The difference between streamers (**diff**) is calculated as `simulated - observed`
- Angles are in radians and are calculated from the closes horizontal axis up
- Suffix `_angle_diff` indicates that this file holds both the angles of correlated streamers, 
and the differences between them.
- Suffix `_angle` indicates that this file holds only the angles of correlated streamers
- Suffix `_diff` indicates that this file holds only the differences between correlated streamers
- The header of each file explains its layout
- `stats.txt` holds statistics on the differences between streamers
