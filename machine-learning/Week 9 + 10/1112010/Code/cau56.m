%
% Author: Truong Minh Anh
% Email: truongminhanh93.it@gmail.com
%

%ham tinh so lan duyet
function [u v iter] = cau56()
    %khoi tao cac gia tri e, so lan duyet va he so hoc rate
    e = 2.71828182846;
    iter = 0;
    rate = 0.1;

    %khoi tao bien tam
    ut = 0;
    vt = 0;

    %khoi tao bien luu he so w
    u = 1;
    v = 1;

    %khoi tao ham do loi
    E = (u*e^v - 2*v*e^(-u))^2;

    %duyet gradient descent
    while (E > 10^-14)
        %cap nhat he so moi vao bien tam
        ut = u - rate * 2 * (u*e^v - 2*v*e^(-u)) * (e^v + 2*v*e^(-u));
        vt = v - rate * 2 * (u*e^v - 2*v*e^(-u)) * (u*e^v - 2*e^(-u));

        %cap nhat vao bien luu he so
        u = ut;
        v = vt;

        %tinh do loi
        E = (u*e^v - 2*v*e^(-u))^2;

        %tang bien duyet
        iter = iter + 1;
    end
end