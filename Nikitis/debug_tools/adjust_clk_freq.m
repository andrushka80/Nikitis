function fclk = adjust_clk_freq(CTRL)

SK_SPAN = 30;

fid = fopen([CTRL.fname '_' num2str(CTRL.dbg_folder) '.txt'],'r');
data = fread(fid);
fclose(fid);

data_char = char(data);

report_idx = findstr(data_char(:)','Sending the measurements report');

% Get timestamp for first report
TS1 = [];
found_lf = 0;
found_sp = 0;
for i=1:SK_SPAN
    
    if (found_lf == 1) && (data_char(report_idx(1) - SK_SPAN + i) == 32)
        found_sp = 1;
    end
    
    if (found_lf == 1) && (found_sp == 0)
        TS1 = [TS1 data_char(report_idx(1) - SK_SPAN + i)];
    end
        
    if data_char(report_idx(1) - SK_SPAN + i) == 10
        found_lf = 1;
    end
end

TS2 = [];
found_lf = 0;
found_sp = 0;
for i=1:SK_SPAN
    
    if (found_lf == 1) && (data_char(report_idx(end) - SK_SPAN + i) == 32)
        found_sp = 1;
    end
    
    if (found_lf == 1) && (found_sp == 0)
        TS2 = [TS2 data_char(report_idx(end) - SK_SPAN + i)];
    end
        
    if data_char(report_idx(end) - SK_SPAN + i) == 10
        found_lf = 1;
    end
end

TS1_num = str2num(TS1);
if TS1_num < 0
    TS1_num = 2^32 + TS1_num;
end

TS2_num = str2num(TS2);
if TS1_num < 0
    TS1_num = 2^32 + TS1_num;
end

fclk = (TS2_num - TS1_num) / (CTRL.report_period * (length(report_idx) - 1));