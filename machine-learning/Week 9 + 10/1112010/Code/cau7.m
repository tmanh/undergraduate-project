%
% Author: Truong Minh Anh
% Email: truongminhanh93.it@gmail.com
%

%ham tinh so lan duyet
function [E] = cau7()
    %khoi tao cac gia tri e, so lan duyet va he so hoc rate
    e = 2.71828182846;
    iter = 0;
    rate = 0.1;

    %khoi tao bien luu he so w
    u = 1;
    v = 1;

    %khoi tao ham do loi
    E = (u*e^v - 2*v*e^(-u))^2;

    %duyet gradient descent
    while (E > 10^-14)
        %cap nhat he so moi vao bien tam
        u = u - rate * 2 * (u*e^v - 2*v*e^(-u)) * (e^v + 2*v*e^(-u));
        
        E = (u*e^v - 2*v*e^(-u))^2;
        if(E > 10^-14)
            v = v - rate * 2 * (u*e^v - 2*v*e^(-u)) * (u*e^v - 2*e^(-u));
        else
            break;
        end

        %tinh do loi
        E = (u*e^v - 2*v*e^(-u))^2;

        %tang bien duyet
        iter = iter + 1;
        
        if(iter == 15)
            break;
        end
    end
end