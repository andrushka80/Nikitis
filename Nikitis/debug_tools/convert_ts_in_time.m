function time = convert_ts_in_time(CTRL, TS_ascii)

% Convert char to num
TS_num = str2num(char(TS_ascii(:)'));
if TS_num < 0
    TS_num = 2^32 + TS_num;
end

% Convert TS in seconds
TS_s = TS_num / CTRL.fclk;

% Add start time
TS_s = TS_s + hms_to_s(CTRL.start_h, CTRL.start_m, CTRL.start_s);

% Convert seconds to h,m,s time
[TS_h, TS_m, TS_s] = s_to_hms(TS_s);

% Get miliseconds
TS_ms = floor((TS_s - floor(TS_s)) * 1000);

% Form time message
time = sprintf('%02dh%02dm%02ds%03dms -',TS_h,TS_m,floor(TS_s),TS_ms);