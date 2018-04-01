%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function [I , Pr] = Nonlinear1()

Pr = 0;
J = 0; %luu tong so lan duyet
N = 1000;
O = ones(1,100);
E = 0;

for i=1:1000,
	%create ten random point
	X = unifrnd(-1, 1, N, 2);
	X = [ones(N,1) X];
	
	%initialize weight matrix
	w = [0 0 0];
	
	%initialize output label matrix
	y = [];
	for p=1:N,
		if(X(p,2)*X(p,2) + X(p,3)*X(p,3) - 0.6 >= 0),
			y = [y 1];
        else
			y = [y -1];
        end
    end
	
	%lay ngau nhien 100 diem nhieu
    ran_mat = round(unifrnd(1, 1000, 100, 1));
    
    for p = 1:100
        y(ran_mat(p)) = - y(ran_mat(p));
    end
	
    %tinh gia tri trong so
	w = pinv(X)*y';

    %kiem thu voi 1000 diem cua tap huan luyen
    signh = (X(:,:) * w);
    
    count = y' .* signh;
    
    t_count = 0;
    
    for i = 1:N
        if(count(i) < 0)
             t_count = t_count + 1;
        end
    end
    
    E = E + t_count;
end

Pr = E / N / 1000;
I = J/1000; %tinh trung binh so lan duyet
end