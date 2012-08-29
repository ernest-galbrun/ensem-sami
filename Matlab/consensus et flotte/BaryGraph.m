function B = BaryGraph(CurrentXPosition,CurrentYPosition,Network)
A = Network+eye(size(Network));
ConnectedNeighbours(1,:) = sum(A)';

Bx = (CurrentXPosition'*A./ConnectedNeighbours)';
By = (CurrentYPosition'*A./ConnectedNeighbours)';
B = [Bx By];
end