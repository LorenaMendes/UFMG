always @(clock == 1) begin
	valor = 0; 
	i = 0; 
	num = 0;
	signal = 0;
	if( identifier == 0) begin //Soma
		valor = inp1 + inp2;

	end else if ( identifier == 1 ) begin //Substração
		valor = inp1 - inp2;
		
	end else if ( identifier == 2 ) begin //Multiplicação
		reginp1 = inp1;
		reginp2 = inp2;
		if((inp1 < 0) && (inp2 < 0)) begin
			signal = 1;
			reginp1 = inp1*-1;
			reginp2 = inp2*-1;
		end else if(inp2 < 0) begin
			signal = 2;
			reginp2 = inp2*-1;
		end else if(inp1 < 0) begin 
			signal = 3;
			reginp1 = inp1*-1;
		end
		
		for(i=0; i<reginp2; i = i + 1) begin
			valor = valor + reginp1;
		end
			
		if((signal == 2) || (signal == 3)) begin
			valor = valor*-1;
		end
		
	end else if ( identifier == 3 ) begin //Divisão
		reginp1 = inp1;
		reginp2 = inp2;
		if((inp1 < 0) && (inp2 < 0)) begin
			signal = 1;
			reginp1 = inp1*-1;
			reginp2 = inp2*-1;
		end else if(inp2 < 0) begin
			signal = 2;
			reginp2 = inp2*-1;
		end else if(inp1 < 0) begin 
			signal = 3;
			reginp1 = inp1*-1;
		end
		
		if((reginp1 >= reginp2) && (reginp2 != 0)) begin
			
			valor = reginp1;
			num = reginp2;
			
			while((valor - num) >= 0) begin
				valor = valor - num;
				i = i + 1;
			end
			
			valor = i;
		end else if(inp1 < inp2) begin
			valor = 0;
		end
		
		if((signal == 2) || (signal == 3)) begin
			valor = valor*-1;
		end
		
	end
	$display("At time D %t, value = %d", $time, valor);
end