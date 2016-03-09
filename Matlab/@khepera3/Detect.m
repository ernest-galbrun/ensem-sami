function [ val ] = Detect()
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
X =ReadRegister([16 33],5);
val = X(12);
end

