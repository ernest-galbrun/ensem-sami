function RWvalue = K3toRW(mode, K3value)
    switch mode
        case 1
            % RW value = 5V is equivalent to PWM target = 1023
           RWvalue = K3value / 1023 * 5;
        case {2,3}
            % Wheel circumference = 128.8 mm
            % 691.2 measures are made for each wheel revolution
            % (we use mode encoder resolution x1)
            RWvalue = K3value / 691.2 * 128.8;
        case {4,5}
            % see manual p. 14
            RWvalue = K3value / 72;
        case 6
            RWvalue = K3value;
    end
end

