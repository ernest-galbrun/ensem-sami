function RWvalue = K3toRW(mode, K3value)
    switch mode
        case 1
            % RW value = 5V is equivalent to PWM target = 1023
           RWvalue = double(K3value) / 1023. * 5;
        case {2,3} %position
            % Wheel circumference = 128.8 mm
            % 691.2 measures are made for each wheel revolution
            % (we use mode encoder resolution x1)
            RWvalue = double(K3value) / 691.2 / 4 * 128.8;
        case {4,5}  %speed
            % see manual p. 14
            RWvalue = double(K3value) / 72. / 4;
        case 6
            RWvalue = double(K3value);
    end
end

