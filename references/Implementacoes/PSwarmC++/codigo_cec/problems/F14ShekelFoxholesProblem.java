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
public class F14ShekelFoxholesProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-65.536, 65.536};

    public F14ShekelFoxholesProblem(Configuration configuration) {
        this.configuration = configuration;
        this.dimension = 2;
    }

    @Override
    protected double[] evaluateSolution(Object gene) {
        double[] x = null;
        if (gene instanceof double[]) {
            x = (double[]) gene;
	    //x[1] = -32;
        } else {
            int[] variableSize = new int[getNumberOfVariables()];
            for (int i = 0; i < variableSize.length; i++) {
                variableSize[i] = configuration.getBinaryEncodingContinuousVariable();
            }
            x = configuration.getUtilitaries().getRealFromBinary((boolean[])gene, variableSize, getBounds(), true, configuration.getBinaryEncodingContinuousVariable(), this);
        }
        double[] result = new double[1];
        double[][] a = {{-32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32},
			{-32, -32, -32, -32, -32, -16, -16, -16, -16, -16, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 32, 32, 32, 32, 32}};
	double sum;
        for (int j = 0; j < a[0].length; j++) {
	    sum = 0;
	    for (int i = 0; i < dimension; i++) {
		sum += Math.pow(x[i]-a[i][j], 6);
	    }
	    result[0] += 1d/((double)j+1+sum);
        }
	result[0] = 1d / (1d/500d + result[0]);
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
	//return 1.22; //FEP
	//return 1.0062;
	return 4.978642; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F14ShekelFoxholesProblem(configuration);
    }
}
