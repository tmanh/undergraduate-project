%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function [I , Pr] = LRFunction1000()

Pr = 0;
J = 0; %luu tong so lan duyet
N = 100;
O = ones(1,100);
E = 0;

for i=1:1000,
	%create random target function
	%ham f co 2 diem duoc tao nam tren 2 truc
	F1 = unifrnd(0.9,1,1,2);   %tao ham f phan chia mot cach dong deu du lieu
    F2 = unifrnd(-1,-0.9,1,2); %tao ham f phan chia mot cach dong deu du lieu
    F3 = [(F1(1,1)*F2(1,2) - F1(1,2)*F2(1,1))/(F1(1,1)-F1(1,2)); (F2(1,1) - F2(1,2))/(F1(1,1) - F1(1,2)); 1];
	
	%create ten random point
	X = unifrnd(-1, 1, N, 2);
	X = [ones(N,1) X];
	
	%initialize weight matrix
	w = [0 0 0];
	
	%initialize output label matrix
	y = [];
	for p=1:N,
		if(X(p,:)*F3 >= 0),
			y = [y 1];
        else
			y = [y -1];
        end
    end
	
    %tinh gia tri trong so
	w = pinv(X)*y';
    
    %tao 1000 diem kiem thu
    tx = unifrnd(-1,1,1000,2);
    tx = [ones(1000,1) tx];
    
    %kiem thu voi 1000 diem cua tap test
    signf = (tx(:,:) * F3);
    signh = (tx(:,:) * w);
    
    count = signh .* signf;
    
    t_count = 0;
    
    for i = 1:1000
        if(count(i) < 0)
             t_count = t_count + 1;
        end
    end
    
    E = E + t_count;
end

Pr = E / 1000 / 1000;
I = J/1000; %tinh trung binh so lan duyet
end