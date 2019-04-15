import numpy as np
import matplotlib.pyplot as plt

'''
Function to plot lines`
'''
def plot_points():
    # generate random data-set
    np.random.seed(5)
    x = np.random.rand(15, 1)*10
    y =  20 * x + np.random.rand(15, 1)*10
    # plot
    with open("p3.txt", "w") as text_file:
        for i in range(len(x)):
            x1=float(x[i])
            y1=float(y[i])
            x1=f'{x1:.4f}'
            y1=f'{y1:.4f}'
            print(x1,y1,file=text_file)

    plt.scatter(x,y,s=10)
    plt.xlabel('x')
    plt.ylabel('y')

    x = np.random.rand(15, 1)*10 + 10
    y =  0.5 * x + np.random.rand(15, 1)*10 + 205
    # plot
    with open("p3.txt", "a") as text_file:
        for i in range(len(x)):
            x1=float(x[i])
            y1=float(y[i])
            x1=f'{x1:.4f}'
            y1=f'{y1:.4f}'
            print(x1,y1,file=text_file)

    plt.scatter(x,y,s=10)
    plt.xlabel('x')
    plt.ylabel('y')

    x = np.random.rand(15, 1)*10 +20
    y =  60 * x + np.random.rand(15, 1)*10 -975
    # plot
    with open("p3.txt", "a") as text_file:
        for i in range(len(x)):
            x1=float(x[i])
            y1=float(y[i])
            x1=f'{x1:.4f}'
            y1=f'{y1:.4f}'
            print(x1,y1,file=text_file)


    plt.scatter(x,y,s=10)
    plt.xlabel('x')
    plt.ylabel('y')

    # return plt

file = open("si.txt",'r')
content_list = []
contents = file.readline()
while len(contents) > 1:
    content_list.append(contents)
    contents = file.readline()



# print(content_list)
slopes = []
intercepts = []

for line in content_list:

    plt.clf()
    plot_points()
        
    if(line!='***\n'):
        slopes.append(line.split(',')[0])
        intercepts.append(line.split(',')[1].split('\n')[0])
        print(line)
    
    if(line=='***\n'):
        print(slopes)
        print(intercepts)
        axes = plt.gca()
        for i in range(len(slopes)):
            x_vals = np.array(axes.get_xlim())
            y_vals = float(intercepts[i]) + float(slopes[i]) * x_vals
            plt.plot(x_vals, y_vals, '--')
        slopes = []
        intercepts = []
        plt.pause(1)




plt.show()