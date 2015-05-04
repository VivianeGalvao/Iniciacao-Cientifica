/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package clonalg_metamodel.problems;

import clonalg_metamodel.util.Configuration;

/**
 *
 * @author hedersb
 */
public class F35CalculadorFortran942BarDiscrete extends F30CalculadorFortran942Bar {

    private double[] tab = {
	0.1, 0.347, 0.1, 0.347, 0.440, 0.539, 0.954, 1.081, 1.174,  
         1.333, 1.488, 1.764, 2.142,2.697, 2.80, 3.131, 3.565, 3.813, 
         4.805, 5.952, 6.572, 7.192, 8.525, 9.30, 10.850,13.330,      
         14.290, 17.170, 19.18, 23.68, 28.08, 33.70
    };

    public F35CalculadorFortran942BarDiscrete(Configuration configuration) {
	super(configuration);
	boundBase = new double[]{0, 32};
    }

    @Override
    public double evaluate(double[] g) {
	double[] x = new double[g.length];
	int i = 0;
	for(double d: g) {
	    //x[i] = tab[(int)Math.round(d)];
	    x[i] = tab[(int)Math.floor(d)];
	    i++;
	}
	return super.evaluate(x);
    }

    @Override
    protected double[] evaluateSolution(Object gene) {
	double[] g = (double[]) gene;
	double[] x = new double[g.length];
	int i = 0;
        int id;
	for(double d: g) {
            id = (int)Math.floor(d);
	    x[i] = tab[ id < tab.length? id: tab.length-1 ];
	    //x[i] = tab[(int)Math.round(d)];
	    //x[i] = (int)Math.round(d);
	    i++;
	}
	return super.evaluateSolution(x);
    }
}
