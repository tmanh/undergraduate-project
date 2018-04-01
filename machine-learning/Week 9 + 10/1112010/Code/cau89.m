%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function [I , Pr] = cau89(k,N,rate)

Pr = 0;
J = 0; %luu tong so lan duyet
e = 2.71828182846;

O = ones(N,1);
O2 = ones(k,1);

for i=1:100
	%create random target function
	%ham f co 2 diem duoc tao nam tren 2 truc
	F = unifrnd(-1,1,1,2); %tao ham f phan chia mot cach dong deu du lieu
	F1 = [1-F(1,1)*F(1,2); F(1,2)+1; (F(1,1)+1)];
	
	%create ten random point
	X1 = unifrnd(-1, 1, N, 2);
	X = [O X1];
	
	%initialize weight matrix
	w_bef = zeros(1,k);
    w_aft = ones(1,k);
    w = zeros(1,k);
	
	%initialize output label matrix
	y = [];
	for p=1:N
		if(X(p,:)*F1 >= 0)
			y = [y 1];
        else
			y = [y -1];
        end
    end
	
    %tinh do loi w khoi tao
    E_w = 1;
    
    count = 1;
    %duyet toi khi muc do thay doi cua w rat nho
    while(E_w > 0.01)
        %choose
        index = round(unifrnd(1,N));
        
        %compute delta_Ein
        delta_Ein = - X(index,:)*y(index) / (1 + e^(X(index,:) * w_bef' * y(index)));
        
        %update
        w = w - rate * delta_Ein;
        
        %compute E_w
        if(count == N)
            w_aft = w;
            E_w = (w_bef - w_aft) .^ 2;
            E_w = sqrt(E_w * O2);
            
            count = 1;
            w_bef = w;
            
            [X y] = shuffle(X, y, N);
            
            J = J + 1;
        end
        
        %update count
        count = count + 1;
    end
    
    %evaluate
    %create ten random point
	X2 = unifrnd(-1, 1, N, 2);
	X_out = [O X2];
    
    %initialize output label matrix
	yout = [];
	for p=1:N
		if(X_out(p,:)*F1 >= 0)
			yout = [yout 1];
        else
			yout = [yout -1];
        end
    end
    
    %compute Eout
    Eout = 0;
    for i = 1:N
    	Eout = Eout + log(1 + e^(- X_out(i,:) * w' * yout(i)));
    end
    %Eout = Eout / N;
    
    Pr = Pr + Eout;
end

Pr = Pr / N / 100;
I = J/100; %tinh trung binh so lan duyet

end

function [X Y] = shuffle(X, Y, N)
    for i = 1:50
        index1 = round(unifrnd(1,N));
        index2 = round(unifrnd(1,N));
        
        T = X(index2,:);
        X(index2,:) = X(index1,:);
        X(index1,:) = T;
        
        tmp = Y(index2);
        Y(index2) = Y(index1);
        Y(index1) = tmp;
        
    end
end

