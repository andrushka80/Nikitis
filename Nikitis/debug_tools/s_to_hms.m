function [h, m, s] = s_to_hms(s)

h = floor(s/3600);
m = floor ( (s - h*3600) / 60);
s = s - h*3600 - m*60;