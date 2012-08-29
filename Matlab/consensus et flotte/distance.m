function d=distance(m1,m2)
d(:,1) = sqrt((m1(:,1)-m2(:,1)).^2+(m1(:,2)-m2(:,2)).^2);
end