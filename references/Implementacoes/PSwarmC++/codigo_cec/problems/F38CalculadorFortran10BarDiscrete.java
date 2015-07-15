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
public class F38CalculadorFortran10BarDiscrete extends F33CalculadorFortran10Bar {

    private double[] tab = {
	1.62,
	1.62,
	1.8,
	1.8,
	1.99,
	2.13,
	2.13,
	2.38,
	2.62,
	2.62,
	2.63,
	2.88,
	2.88,
	2.93,
	3.09,
	3.09,
	3.13,
	3.38,
	3.38,
	3.47,
	3.55,
	3.55,
	3.63,
	3.84,
	3.84,
	3.87,
	3.88,
	3.88,
	4.18,
	4.22,
	4.22,
	4.49,
	4.59,
	4.59,
	4.8,
	4.8,
	4.97,
	5.12,
	5.12,
	5.74,
	7.22,
	7.22,
	7.97,
	11.5,
	11.5,
	13.5,
	13.9,
	13.9,
	14.2,
	15.5,
	15.5,
	16.0,
	16.9,
	16.9,
	18.8,
	19.9,
	19.9,
	22.0,
	22.9,
	22.9,
	26.5,
	30.0,
	30.0,
	33.5
    };

    public F38CalculadorFortran10BarDiscrete(Configuration configuration) {
	super(configuration);
	boundBase = new double[]{0, 64};
    }

    @Override
    public double evaluate(double[] g) {
	double[] x = new double[g.length];
	int i = 0;
	for (double d : g) {
	    //x[i] = tab[(int)Math.round(d)];
	    x[i] = tab[(int) Math.floor(d)];
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
	for (double d : g) {
            id = (int) Math.floor(d);
	    //x[i] = tab[(int) Math.floor(d)];
            x[i] = tab[ id < tab.length? id: tab.length-1 ];
	    //x[i] = tab[(int)Math.round(d)];
	    //x[i] = (int)Math.round(d);
	    i++;
	}
	return super.evaluateSolution(x);
    }
}
