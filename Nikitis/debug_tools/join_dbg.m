function found = join_dbg(CTRL)

found = -1;
first = 1;
count = 0;

while 1
    fname = ['./' CTRL.dbg_folder '/Debug' num2str(count) '.txt'];
    fidr = fopen(fname,'r');
    if fidr~=-1
        found = 1;
        data = fread(fidr);
        fclose(fidr);
        if first
            fidw = fopen([CTRL.fname '_' num2str(CTRL.dbg_folder) '.txt'],'w');
            first = 0;
        else
            fidw = fopen([CTRL.fname '_' num2str(CTRL.dbg_folder) '.txt'],'a');
        end
        fwrite(fidw,data);
        fclose(fidw);
        count = count + 1;
    else
        break;
    end
end