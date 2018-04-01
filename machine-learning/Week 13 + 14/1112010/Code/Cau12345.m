%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function [Eout] = Cau12345(IX, IY, OX, OY)
    Ein = [0 0 0 0 0];
    Eout = [0 0 0 0 0];
    N = 1000;
    
    O = ones(length(IX),1);
    AIX1 = [O IX IX(:,1).^2];
    AIX2 = [O IX IX(:,1).^2 IX(:,2).^2];
    AIX3 = [O IX IX(:,1).^2 IX(:,2).^2 IX(:,1).*IX(:,2)];
    AIX4 = [O IX IX(:,1).^2 IX(:,2).^2 IX(:,1).*IX(:,2) abs(IX(:,1)-IX(:,2))];
    AIX5 = [O IX IX(:,1).^2 IX(:,2).^2 IX(:,1).*IX(:,2) abs(IX(:,1)-IX(:,2)) abs(IX(:,1)+IX(:,2))];
    
    O = ones(length(OX),1);
    
    AOX1 = [O OX OX(:,1).^2];
    AOX2 = [O OX OX(:,1).^2 OX(:,2).^2];
    AOX3 = [O OX OX(:,1).^2 OX(:,2).^2 OX(:,1).*OX(:,2)];
    AOX4 = [O OX OX(:,1).^2 OX(:,2).^2 OX(:,1).*OX(:,2) abs(OX(:,1)-OX(:,2))];
    AOX5 = [O OX OX(:,1).^2 OX(:,2).^2 OX(:,1).*OX(:,2) abs(OX(:,1)-OX(:,2)) abs(OX(:,1)+OX(:,2))];

        for i=1:N,
            %tinh gia tri trong so
            w1 = pinv(AIX1) *IY;
            w2 = pinv(AIX2) *IY;
            w3 = pinv(AIX3) *IY;
            w4 = pinv(AIX4) *IY;
            w5 = pinv(AIX5) *IY;

            %tinh Ein
            H1 = AIX1 * w1;
            H2 = AIX2 * w2;
            H3 = AIX3 * w3;
            H4 = AIX4 * w4;
            H5 = AIX5 * w5;
            
            D1 = (H1 .* IY);
            D2 = (H2 .* IY);
            D3 = (H3 .* IY);
            D4 = (H4 .* IY);
            D5 = (H5 .* IY);
            
            for p = 1:length(D1)
                if(D1(p)<0)
                    Ein(1) = Ein(1) + 1;
                end
            end
            Ein(1) = Ein(1) / length(D1); 
            
            for p = 1:length(D2)
                if(D2(p)<0)
                    Ein(2) = Ein(2) + 1;
                end
            end
            Ein(2) = Ein(2) / length(D2); 
            
            for p = 1:length(D3)
                if(D3(p)<0)
                    Ein(3) = Ein(3) + 1;
                end
            end
            Ein(3) = Ein(3) / length(D3); 
            
            for p = 1:length(D4)
                if(D4(p)<0)
                    Ein(4) = Ein(4) + 1;
                end
            end
            Ein(4) = Ein(4) / length(D4); 
            
            for p = 1:length(D5)
                if(D5(p)<0)
                    Ein(5) = Ein(5) + 1;
                end
            end
            Ein(5) = Ein(5) / length(D5); 

            %tinh Eout
            H1 = AOX1 * w1;
            H2 = AOX2 * w2;
            H3 = AOX3 * w3;
            H4 = AOX4 * w4;
            H5 = AOX5 * w5;
            
            D1 = (H1 .* OY);
            D2 = (H2 .* OY);
            D3 = (H3 .* OY);
            D4 = (H4 .* OY);
            D5 = (H5 .* OY);
            
            for p = 1:length(D1)
                if(D1(p)<0)
                    Eout(1) = Eout(1) + 1;
                end
            end
            Eout(1) = Eout(1) / length(D1);
            
            for p = 1:length(D2)
                if(D2(p)<0)
                    Eout(2) = Eout(2) + 1;
                end
            end
            Eout(2) = Eout(2) / length(D2);
            
            for p = 1:length(D3)
                if(D3(p)<0)
                    Eout(3) = Eout(3) + 1;
                end
            end
            Eout(3) = Eout(3) / length(D3);
            
            for p = 1:length(D4)
                if(D4(p)<0)
                    Eout(4) = Eout(4) + 1;
                end
            end
            Eout(4) = Eout(4) / length(D4);
            
            for p = 1:length(D5)
                if(D5(p)<0)
                    Eout(5) = Eout(5) + 1;
                end
            end
            Eout(5) = Eout(5) / length(D5);
        end
end