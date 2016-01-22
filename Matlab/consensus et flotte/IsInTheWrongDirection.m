function Answer = IsInTheWrongDirection(CurrentOrientation,GoalOrientation,epsilonA)
% This function tests if each robot has the right orientation or not.
% Angles must be counted only positively.
%

Answer = gt(max(CurrentOrientation,GoalOrientation)-min(CurrentOrientation,GoalOrientation),epsilonA);


end