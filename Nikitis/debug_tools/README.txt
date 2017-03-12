Run instructions:
-----------------
1. Copy the debug session subfolder from SD card into this folder (e.g.: SD:/Debug/14 copied as folder named 14 into the folder where this README resides)
2. Open the dbg_log_tools.m in Matlab
3. Set the CONFIG basic parameters accordingly:
	CTRL.dbg_folder: give the name of the subfolder copied from SD card (e.g. 14)
	CTRL.start_h, CTRL.start_m, CTRL.start_s: provide the time when the mote started
4. Run dbg_log_tools.m script

Outputs:
--------
1. Debug_join_<subfolder_name>_join.txt -> represents a merged file containing all the logging files within the <subfolder_name> folder
2. Debug_converted_<subfolder_name>.txt -> represets the merged file, but now with the timestamps replaced with the absolute time in h:m:s:ms
3. Matlab plots the x,y,z and sqrt(x^2 + y^2 + z^2)

Requirements:
-------------
All these Matlab scripts have been tested with MATLAB R2015a