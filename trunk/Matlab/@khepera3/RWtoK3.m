function K3value = RWtoK3(mode, RWvalue)
    switch mode
        case 1
            % RW value = 5V is equivalent to PWM target = 1023
            K3value = RWvalue * 1023 / 5;
        case {2,3}
            % Wheel circumference = 128.8 mm
            % 691.2 measures are made for each wheel revolution
            % (we use mode encoder resolution x1)
            K3value = RWvalue * 691.2 / 128.8;
        case {4,5}
            % see manual p. 14
            K3value = RWvalue * 144.01 * 4;
        case 6
            K3value = RWvalue;
    end
    K3value = int32(round(K3value));
end

