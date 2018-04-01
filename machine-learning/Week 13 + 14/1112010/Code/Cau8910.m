%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function [number_alpha pPLA, pSVM] = Cau8910(k)

pPLA = 0;
pSVM = 0;
number_alpha = 0;

options = optimset('Algorithm', 'interior-point-convex', 'MaxIter',1500, 'Display', 'off');

for i=1:1000,
	%create random target function
	%ham f co 2 diem duoc tao nam tren 2 truc
	F = unifrnd(-1,1,2,2); %tao ham f phan chia mot cach dong deu du lieu
	F1 = [(F(1,2) - F(2,2))/(F(1,1) - F(2,1)); (F(1,2)*F(2,1) - F(2,2)*F(1,1))/(F(1,1) - F(2,1))];
	
	%create ten random point
	X1 = unifrnd(-1, 1, k, 2);
	X = [ones(k,1) X1];
	
	%initialize weight matrix for PLA
	wPLA = [0 0 0];
	
	%initialize output label matrix
	y = [];
	for p=1:k,
		if(X(p,3) - polyval(F1, X1(p, 1))>= 0),
			y = [y 1];
        else
			y = [y -1];
        end
    end
	
	%duyet toi da 1000 lan
	for j=1:1000,
		tmp = [];	%luu vi tri cac diem phan lop sai
		for k = 1:k,
			if(wPLA*X(k,:)' >= 0),
				t_sign = 1;
            else
				t_sign = -1;
            end
			
			if(t_sign ~= y(k)),
				tmp = [tmp k];
            end
        end
		
		%neu chieu dai vector luu cac diem phan sai lop la 0 thi dung
		if(length(tmp) <= 0),
			j = j - 1;
			break;
		%neu chieu dai bang 1 chon mac dinh diem phan sai
		elseif (length(tmp) == 1),
			wPLA = wPLA + X(tmp(1),:) * y(tmp(1));
		%neu chieu dai lon hon 1 thi chon ngau nhien diem phan sai
        else
			t = round(unifrnd(1,length(tmp),1));
			wPLA = wPLA + X(tmp(t),:) * y(tmp(t));
        end
    end;
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    SVMX = [X(:,2) X(:,3)];
    
    alphaY = y'*y;
    alphaX = SVMX * SVMX';
    
    Q = alphaY .* alphaX;
    f = -1 * ones(1,k);
    
    lb = zeros(k, 1);
	ub = 1e6*ones(k, 1);
    
    %compute alpha
    alpha = quadprog(Q,f,[],[],y,0,lb,ub,[],options);
    
    number_of_alpha = alpha(:) > 1e-6;
    number_of_alpha =  ones(1,k) * number_of_alpha;
    number_alpha = number_of_alpha + number_alpha;
    
    %compute WSVM
    tmp = (alpha .* y');
    tmp = [tmp tmp];
    wSVM = SVMX .* tmp;
    wSVM = -f * wSVM;

    %compute b
    tmp = wSVM * SVMX';
    [min_value index] = max(alpha);
    b = 1/y(index) - wSVM * SVMX(index, :)';
    
    wSVM = [b wSVM];
    
    tx = unifrnd(-1,1,1000,2);
    tx = [ones(1000,1) tx];
    signf = tx(:,3) - polyval(F1, tx(:, 2));
    
    %----------------------------------------
    signh = (wPLA * tx(:,:)');
    
    count = signh' .* signf;
    
    t_count = 0;
    
    for (i = 1:1000)
        if(count(i) < 0)
             t_count = t_count + 1;
        end
    end
    
    PrPLA = t_count;
    
    %----------------------------------------
    signh = (wSVM * tx(:,:)');
    
    count = signh' .* signf;
    
    t_count = 0;
    
    for (i = 1:1000)
        if(count(i) < 0)
             t_count = t_count + 1;
        end
    end
    
    PrSVM = t_count;
    
    if(PrPLA < PrSVM)
        pPLA = pPLA + 1;
    else
        pSVM = pSVM + 1;
    end
    
end

sum_all = (pPLA + pSVM);
pPLA = pPLA / sum_all;
pSVM = pSVM / sum_all;
number_alpha = number_alpha / 1000;

end