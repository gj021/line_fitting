#include <bits/stdc++.h>

using namespace std;
/**
 * @brief Class which contains functions to calculate such as sigma(X),sigma(Y),sigma(XY),slope and intercept of best fit line
 * 
 */
class Operation
{
    public:
    /**
     * @brief Function to tokenize each line of file to get the value of points
     * 
     * @param str Line of the input file
     * @param delimiter Delimter to break the string into tokens 
     * @return vector<string> Vector of strings which contains points value
     */
    vector<string> split(string str, char delimiter) 
    {
        vector<string> internal;
        stringstream ss(str); // Turn the string into a stream.
        string tok;
        
        while(getline(ss, tok, delimiter)) 
        {
            internal.push_back(tok);
        }
        
        return internal;
    }
    
    /**
     * @brief To calculate the sum of multiplication of x-coordinate and y-coordinate  of points
     * 
     * @param start Starting index of points for which best line needs to be calculated
     * @param end   Ending index of points for which best line needs to be calculated
     * @return double Sigma(x*y)
     */
    double mul_pairs(vector <pair <double,double> >points,int start,int end)
    {
        double sum=0;
        for(int i=start;i<=end;i++)
        {
            sum=sum+points[i].first*points[i].second;
        }
        return sum;
    }

    /**
     * @brief To calculate the sum of  x-coordinate of points 
     * 
     * @param start Starting index of points for which best line needs to be calculated
     * @param end   Ending index of points for which best line needs to be calculated
     * @return double Sigma(x)
     */
    double sumX(vector <pair <double,double> >points,int start,int end)
    {
        double sum=0;
        for(int i=start;i<=end;i++)
        {
            sum=sum+points[i].first;
        }
        return sum;
    }

    /**
     * @brief To calculate the sum of y-coordinate of points 
     * 
     * @param start Starting index of points for which best line needs to be calculated
     * @param end   Ending index of points for which best line needs to be calculated
     * @return double Sigma(y)
     */
    double sumY(vector <pair <double,double> >points,int start,int end)
    {
        double sum=0;
        for(int i=start;i<=end;i++)
        {
            sum=sum+points[i].second;
        }
        return sum;
    }

   /**
     * @brief To calculate the sum of squares of x-coordinate of points 
     * 
     * @param start Starting index of points for which best line needs to be calculated
     * @param end   Ending index of points for which best line needs to be calculated
     * @return double Sigma(x^2)
     */
    double sumX2(vector <pair <double,double> >points,int start,int end)
    {
        double sum=0;
        for(int i=start;i<=end;i++)
        {
            sum=sum+points[i].first*points[i].first;
        }
        return sum;
    }

    /**
     * @brief To calculate the slope and intercept of the best fit lines between set of points {pi,pi+1,............,pj}
     * 
     * @param start Starting index of points for which best line needs to be calculated
     * @param end  Ending index of points for which best line needs to be calculated
     * @return pair<double,double> Slope and Intercept of the best fit line
     */
    pair<double,double> calc_slope_intercept(vector <pair <double,double> >points,int start,int end)
    {
       
        int n=end-start+1;

        double sigma_xy=mul_pairs(points,start,end);
        double sigma_x=sumX(points,start,end);
        double sigma_y=sumY(points,start,end);
        double sigma_x2=sumX2(points,start,end);
        double slope=(n*sigma_xy-(sigma_x*sigma_y))/((n*sigma_x2)-(sigma_x*sigma_x));
        double intercept=(sigma_y-slope*sigma_x)/n;

        pair <double,double> temp;

        if(start==96 && end==97)
        {
            cout<<(n*sigma_x2)-(sigma_x*sigma_x)<<endl;     
        }    

        temp.first=slope;
        temp.second=intercept;

        return temp;
    }

};

/**
 * @brief Class to store in points in a vector and to calculate the value of error,slope and intercept
 * 
 */
class Points{
    public:
    int numPt;//!< To store number of points
    vector <pair <double,double> >points; //!< A vector which holds the entire graph's coordinates 
    vector <vector <double>> err;//!< Vector to store error of best fit line between two points i and j
    vector <vector <double>> slope; //!< Vector to store slope of best fit line between two points i and j
    vector <vector <double>> intercept;//!< Vector to store intercept of best fit line between two points i and j

    /**
     * @brief Preprocessing of points given as file input to store the points in a vector
     * 
     * @param str1 File_Name which contains input points
     */
    void takeInput(string str1)
    {
        numPt = 0;
        Operation op;
        ifstream file(str1);
        string str;
        int count=0;
        while (getline(file, str))
        {
            vector <string> p=op.split(str,' ');
            points.push_back(make_pair(stof(p[0]), stof(p[1])));
            numPt++;
        }
    }

    /**
     * @brief To sort the points by x-coordinate
     * 
     */
    void sortByx()
    {
        sort(points.begin(), points.end());
    }

    /**
     * @brief To store slope,error,intercept of best fit line between set of points {pi,pi+1,............,pj} in a vector
     * 
     */
    void  calc_error()
    {
         
        for(int i=0;i<points.size();i++)
        {
            Operation op;
            for(int j=0;j<=i;j++)
            {
                if(j!=i)
                {
                    pair <double,double> result=op.calc_slope_intercept(points,j,i);
                    double slope_=result.first;
                    double intercept_=result.second;
                    slope[j][i]=slope_;
                    intercept[j][i]=intercept_;
                    slope[i][j]=slope_;
                    intercept[i][j]=intercept_;
                    double error=0.0;
                    for(int k=j;k<=i;k++)
                    {
                        double temp=points[k].second-slope_*points[k].first-intercept_;
                        error=error+temp*temp;
                    }
                    err[i][j]=error;
                    err[j][i]=error;
                }
                else
                {
                    err[i][j]=INT_MAX;
                    slope[j][i]=INT_MAX;
                    intercept[j][i]=INT_MAX;
                }
            }
        }
    }
};
