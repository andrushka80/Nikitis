clear
clc
% close all


fid = fopen('Debug_join_7_aux.txt','r');
data = fread(fid);
fclose(fid);

data_char = char(data);

% GET FIELD VALUES
FILE_START = findstr(data_char(:)','- x');
data_char2 = data_char(FILE_START(1):end)';

x_pos = findstr(data_char2,'- x');
y_pos = findstr(data_char2,'- y');
z_pos = findstr(data_char2,'- z');

Hx0 = -285.1;
Hy0 = -224.3;
Hz0 = -1178;

num_records = min([length(x_pos) length(y_pos) length(z_pos)]);

field_data = zeros(num_records, 4);

for i=1:num_records
    end_of_num = findstr(data_char2((x_pos(i)):(x_pos(i)+30)),'milli');
    field_data(i,2) = str2num(data_char2((x_pos(i)+3):(x_pos(i)+end_of_num(1)-2)))-Hx0;
    end_of_num = findstr(data_char2((y_pos(i)):(y_pos(i)+30)),'milli');
    field_data(i,3) = str2num(data_char2((y_pos(i)+3):(y_pos(i)+end_of_num(1)-2)))-Hy0;
    end_of_num = findstr(data_char2((z_pos(i)):(z_pos(i)+30)),'milli');
    field_data(i,4) = str2num(data_char2((z_pos(i)+3):(z_pos(i)+end_of_num(1)-2)))-Hz0;
end
text_to_pr = repmat('aa',num_records,1);

% GET TIMESTAMPS (x only)
data_char2 = data_char';
x_pos2 = findstr(data_char2,'- x');

for i=1:num_records
    find_lf = findstr(data_char2((x_pos2(i)-30):(x_pos2(i))),char(10));
    field_data(i,1) = str2num(data_char2((x_pos2(i)-30 + find_lf(end)):(x_pos2(i)-1)));
end

figure(1), plot(field_data(:,1), field_data(:,2)), grid;
hold on
figure(1), plot(field_data(:,1), field_data(:,3),'r');
figure(1), plot(field_data(:,1), field_data(:,4),'g')
figure(1), plot(field_data(:,1), sqrt(field_data(:,2).^2 + field_data(:,3).^2 + field_data(:,4).^2),'k','LineWidth',2), legend('x axis','y axis','z axis','Modulus');
hold off

% figure(2), plot(field_data(:,1), (field_data(:,2).^2 + field_data(:,3).^2 + field_data(:,4).^2),'k','LineWidth',2), grid, legend('SQUARED');