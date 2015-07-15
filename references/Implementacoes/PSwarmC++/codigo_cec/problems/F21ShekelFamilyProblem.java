/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package clonalg_metamodel.problems;

import clonalg_metamodel.base.Problem;
import clonalg_metamodel.util.Configuration;
import clonalg_metamodel.util.Vector;

/**
 *
 * @author hedersb
 */
public class F21ShekelFamilyProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {0, 10};

    public F21ShekelFamilyProblem(Configuration configuration) {
        this.configuration = configuration;
        this.dimension = 4;
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
	double[][] a = {{4, 4, 4, 4},
			{1, 1, 1, 1},
			{8, 8, 8, 8},
			{6, 6, 6, 6},
			{3, 7, 3, 7}};
	double[] c = {0.1, 0.2, 0.2, 0.4, 0.4};
	double[] aux;
	int m = 5;
	for (int i = 0; i < m; i++) {
	    aux = new double[dimension];
	    for (int j = 0; j < dimension; j++) {
		aux[j] = x[j] - a[i][j];
	    }
	    result[0] -= 1d/(Vector.product(aux, aux) + c[i]);
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
	//return -5.52; //FEP
	//return -7.59;
	return -2.326823; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F21ShekelFamilyProblem(configuration);
    }

}
