function Answer = IsTooFar(CurrentPosition,GoalPosition,epsilonP)
% This function test if the current position of robots is in a circle
% centered on the goal position with a radius of epsilonP.
%
% Inputs : 
%   - CurrentPosition : Matrix of current positions. It must have this
%   structure :  [x1,y1;
%                x2,y2;
%                 ...
%                xn,yn]
%   - GoalPosition : Matrix representing the position each robot has to
%   reach. It has the same structure as the CurrentPosition matrix.
%   - epsilonP : Column vector (nx1) representing the radius of the circle 
%   in which robots has to be in order to get a negative test i.e. in order
%   to be close enough of the goal position.
%
% Output : 
%   - Answer : Column vector filled with logical 1 or 0. If Answer(i,1) = 1
%   it means that the robot n°i is too far from GoalPosition(i)
%
%   any or all should be use to treat the answer of this function
X = CurrentPosition(:,1)-GoalPosition(:,1);
Y = CurrentPosition(:,2)-GoalPosition(:,2);
Answer = gt(X.^2+Y.^2,epsilonP.^2);

end