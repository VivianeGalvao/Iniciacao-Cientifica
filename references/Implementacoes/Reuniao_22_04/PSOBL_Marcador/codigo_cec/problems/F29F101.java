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
public class F29F101 extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-512, 512};

    public F29F101(Configuration configuration, int dimension) {
	this.dimension = dimension;
	this.configuration = configuration;
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
	double sum = 0.0;
	for (int i = 0; i < dimension-1; i++) {
	    sum += (-x[i] * Math.sin(Math.sqrt(Math.abs(x[i] - (x[i+1] + 47)))) - (x[+1] + 47) * Math.sin(Math.sqrt(Math.abs(x[i+1] + 47 + (x[i] / 2)))));
	}
	result[0] = sum;
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
	//return 150000;
	return 15000;
    }

    @Override
    public double getBestValue() {
	throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Problem clone() {
	return new F29F101(configuration, dimension);
    }

}
