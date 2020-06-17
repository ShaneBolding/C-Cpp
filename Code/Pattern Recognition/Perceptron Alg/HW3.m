clear

%defining the classes
Class1 = [0.15 0.9 ; 0.1 0.5 ; -0.2 0.4 ; 0.05 0.6];
Class2 = [0.8 0.3 ; 0.55 -0.15 ; 0.4 0 ; 0.68 .45];
%part a plotting
plot(Class1(:,1),Class1(:,2),'b*'); hold on; plot(Class2(:,1),Class2(:,2),'gs');
%part b 
line = perceptron_batch(Class1,Class2,.1,20);
linex = -1:0.1:1;
liney = (-line(1)*linex - line(3))/line(2);
plot(linex,liney,'k');
%part c
online = perceptron_batch_online(Class1,Class2,.1,20);
onlinex = -1:0.1:1;
onliney = (-online(1)*onlinex - online(3))/online(2);
plot(onlinex,onliney,'m');
%part d
w = sum_of_error(Class1,Class2);
wx = -1:0.1:1;
wy = (-w(1)*wx - w(3))/w(2);
plot(wx,wy,'g');


    
