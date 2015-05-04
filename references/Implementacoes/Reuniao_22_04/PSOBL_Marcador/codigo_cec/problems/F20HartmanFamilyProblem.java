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
public class F20HartmanFamilyProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {0, 1};

    public F20HartmanFamilyProblem(Configuration configuration) {
        this.configuration = configuration;
        this.dimension = 6;
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
	double[][] a = {{10, 3, 17, 3.5, 1.7, 8},
			{0.05, 10, 17, 0.1, 8, 14},
			{3, 3.5, 1.7, 10, 17, 8},
			{17, 8, 0.05, 10, 0.1, 14}};
	double[] c = {1, 1.2, 3, 3.2};
	double[][] p = {{0.1312, 0.1696, 0.5569, 0.0124, 0.8283, 0.5886},
			{0.2329, 0.4135, 0.8307, 0.3736, 0.1004, 0.9991},
			{0.2348, 0.1415, 0.3522, 0.2883, 0.3047, 0.6650},
			{0.4047, 0.8828, 0.8732, 0.5743, 0.1091, 0.0381}};
	double aux;
	double sum;
	for (int i = 0; i < c.length; i++) {
	    sum = 0;
	    for (int j = 0; j < dimension; j++) {
		aux = x[j]-p[i][j];
		sum -= a[i][j]*aux*aux;
	    }
	    result[0] -= c[i]*Math.exp(sum);
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
        //return 20000;
	return 2000;
    }

    @Override
    public double getBestValue() {
	//return -3.27; //FEP
	//return -3.3;
	return -3.060915; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F20HartmanFamilyProblem(configuration);
    }

}
