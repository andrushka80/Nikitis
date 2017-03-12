function [] = TS_parse(CTRL)

% Open debug file
fid = fopen([CTRL.fname '_' num2str(CTRL.dbg_folder) '.txt'],'r');
t_ascii_r = fread(fid);
fclose(fid);

% Define states
COPY_TXT         = 0;
EXPECT_DIGIT     = 1;
ACCUM_TS         = 2;
VALID_TS         = 3;
FLUSH_TXT        = 4;
CONVERT_TS       = 5;

% Process text char by char

% Inits
cursor_r=1;
cursor_w=1;
temp_cursor_w = 1;
TS_cursor = 1;
reading = 1;
state = EXPECT_DIGIT;

t_ascii_w = zeros(length(t_ascii_r),1);
temp_w = zeros(30,1);
TS_ascii = zeros(30,1);

while (reading)
    
    % STATE TRANSITION LOGIC
    switch state
        case COPY_TXT
            if t_ascii_r(cursor_r) == 10 % new line
                state = EXPECT_DIGIT;
            end
            
        case EXPECT_DIGIT
            if ((t_ascii_r(cursor_r) >= 48) && (t_ascii_r(cursor_r) <= 57)) || (t_ascii_r(cursor_r) == 45) % is digit
                state = ACCUM_TS;
                temp_cursor_w = 1;
                TS_cursor = 1;
            else
                state = COPY_TXT;
            end
            
        case ACCUM_TS
            if ~((t_ascii_r(cursor_r) >= 48) && (t_ascii_r(cursor_r) <= 57)) % is not a digit
                if t_ascii_r(cursor_r) == 32 % space
                    state = VALID_TS;
                else
                    state = FLUSH_TXT;
                end
            end
            
        case VALID_TS
            if t_ascii_r(cursor_r) == 45 % -
                state = CONVERT_TS;
            else
                state = FLUSH_TXT;
            end
            
        case FLUSH_TXT
            state = COPY_TXT;
            
        case CONVERT_TS
            state = COPY_TXT;
    
    end
    
    % STATE PROCESSING
    switch state
        case COPY_TXT
            % Copy the text as is
            t_ascii_w(cursor_w) = t_ascii_r(cursor_r);
            cursor_w = cursor_w + 1;
            
        case EXPECT_DIGIT
            % Copy the text as is
            t_ascii_w(cursor_w) = t_ascii_r(cursor_r);
            cursor_w = cursor_w + 1;
            
        case ACCUM_TS
            % Save TS sepparately
            TS_ascii(TS_cursor) = t_ascii_r(cursor_r);
            temp_w(temp_cursor_w) = t_ascii_r(cursor_r);
            TS_cursor = TS_cursor + 1;
            temp_cursor_w = temp_cursor_w + 1;      
            
        case VALID_TS
            % Pending on validation character; just copy in temp buffer
            temp_w(temp_cursor_w) = t_ascii_r(cursor_r);
            
        case FLUSH_TXT
            % TS invalidated; flush the temp buffer onto the write buffer
            for i=1:temp_cursor_w
                t_ascii_w(cursor_w) = temp_w(i);
                cursor_w = cursor_w + 1;
            end
            % Also write the current character
            t_ascii_w(cursor_w) = t_ascii_r(cursor_r);
            cursor_w = cursor_w + 1;
            
        case CONVERT_TS
            % TS validated; do the conversion and save
            TS_converted = convert_ts_in_time(CTRL, TS_ascii(1:(TS_cursor-1)));
            
            for i=1:length(TS_converted)
                t_ascii_w(cursor_w) = TS_converted(i);
                cursor_w = cursor_w + 1;
            end
    end
    
    if cursor_r == length(t_ascii_r)
        reading = 0;
    end
    
    cursor_r = cursor_r + 1;
    
end % while reading
                
fid = fopen([CTRL.parse_fname '_' num2str(CTRL.dbg_folder) '.txt'],'w');
fwrite(fid, t_ascii_w(1:(cursor_w-1)));
fclose(fid);
            