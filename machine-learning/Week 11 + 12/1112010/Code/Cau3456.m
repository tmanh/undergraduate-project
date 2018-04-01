%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function [Ein Eout] = Cau3456(IX, IY, OX, OY, k)
    Ein = 0;
    Eout = 0;
    N = 1000;

    O = ones(length(IX),1);
    IX = [O IX IX(:,1).^2 IX(:,2).^2 IX(:,1).*IX(:,2) abs(IX(:,1)-IX(:,2)) abs(IX(:,1)+IX(:,2))];
    O = ones(length(OX),1);
    OX = [O OX OX(:,1).^2 OX(:,2).^2 OX(:,1).*OX(:,2) abs(OX(:,1)-OX(:,2)) abs(OX(:,1)+OX(:,2))];
    
    I = eye(8);
    lambda = 10^k;

    for i=1:N,
        %tinh gia tri trong so
        w = ((IX'*IX + lambda*I ) ^ -1)* IX' *IY;

        %tinh Ein
        H = IX * w;
        D = (H .* IY);
        for p = 1:length(D)
            if(D(p)<0)
                Ein = Ein + 1;
            end
        end
        Ein = Ein / length(D); 

        %tinh Eout
        H = OX * w;
        D = (H .* OY);
        for p = 1:length(D)
            if(D(p)<0)
                Eout = Eout + 1;
            end
        end
        Eout = Eout / length(D);
    end
end