clear
clc
close all

% CONFIG basic
CTRL.dbg_folder = '8';
CTRL.start_h = 9;
CTRL.start_m = 42;
CTRL.start_s = 30;

% CONFIG advanced
CTRL.fclk = 62487.64; % Hz
CTRL.report_period = 15 * 60; % s
CTRL.fname = 'Debug_join';
CTRL.parse_fname = 'Debug_converted';

% Join files
msg = sprintf('Joining dbg files...');
disp(msg);
join_dbg(CTRL);

% Adjust clock frequency
% msg = sprintf('Adjusting clock frequency...');
% disp(msg);
% CTRL.fclk = adjust_clk_freq(CTRL);

% Call TS parse
msg = sprintf('Converting...');
disp(msg);
TS_parse(CTRL);

% Call field plot
msg = sprintf('Ploting...');
disp(msg);
field_plot(CTRL);

msg = sprintf('DONE!!!');
disp(msg);