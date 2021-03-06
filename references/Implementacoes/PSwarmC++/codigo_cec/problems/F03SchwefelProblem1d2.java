/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package clonalg_metamodel.problems;

import clonalg_metamodel.base.Problem;
import clonalg_metamodel.util.Configuration;

/**
 *
 * @author hedersb
 */
public class F03SchwefelProblem1d2 extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-100, 100};

    public F03SchwefelProblem1d2(Configuration configuration, int dimension) {
        this.configuration = configuration;
        this.dimension = dimension;
    }

    @Override
    protected double[] evaluateSolution(Object gene) {
        double[] x = null;
        if (gene instanceof double[]) {
            x = (double[]) gene;
        } else {
            int[] variableSize = new int[getNumberOfVariables()];
            for (int i = 0; i < variableSize.length; i++) {
                variableSize[i] = configuration.getBinaryEncodingContinuousVariable();
            }
            x = configuration.getUtilitaries().getRealFromBinary((boolean[])gene, variableSize, getBounds(), true, configuration.getBinaryEncodingContinuousVariable(), this);
        }
        double[] result = new double[1];
	double summation;
        for (int i = 0; i < dimension; i++) {
	    summation = 0;
	    for (int j = 0; j < i; j++) {
		summation += x[j]*x[j];
	    }
	    result[0] += summation;
        }
        return result;
    }

    @Override
    public double[][] getBounds() {
        if (bound==null) {
            bound = new double[dimension][2];
            for (int i = 0; i < bound.length; i++) {
                bound[i][0] = boundBase[0];
                bound[i][1] = boundBase[1];
            }
        }
        return bound;
    }

    @Override
    public int getMaxNumberFitnessFuntionEvaluation() {
        //return 500000;
	//return 50000;
	return 40000; //usado no paper EI2010
    }

    @Override
    public double getBestValue() {
	//return 1.6*Math.pow(10, -2); //FEP
	//return 22000;
	return 0.00000000000000009781800; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F03SchwefelProblem1d2(configuration, dimension);
    }

}
