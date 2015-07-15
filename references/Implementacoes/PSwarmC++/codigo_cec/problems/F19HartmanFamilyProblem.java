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
public class F19HartmanFamilyProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {0, 1};

    public F19HartmanFamilyProblem(Configuration configuration) {
        this.configuration = configuration;
        this.dimension = 3;
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
	double[][] a = {{3, 10, 30},
			{0.1, 10, 35},
			{3, 10, 30},
			{0.1, 10, 35}};
	double[] c = {1, 1.2, 3, 3.2};
	double[][] p = {{0.3689, 0.1170, 0.2673},
			{0.4699, 0.4387, 0.7470},
			{0.1091, 0.8732, 0.5547},
			{0.038150, 0.5743, 0.8828}};
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
        //return 10000;
	return 1000;
    }

    @Override
    public double getBestValue() {
	//return -3.86; //FEP
	//return -3.71;
	return -3.830570; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F19HartmanFamilyProblem(configuration);
    }

}
