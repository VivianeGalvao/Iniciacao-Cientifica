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
public class F10AckleyProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-1, 1};

    public F10AckleyProblem(Configuration configuration, int dimension) {
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
        double sum1 = 0;
        double sum2 = 0;
        for (int i = 0; i < dimension; i++) {
            sum1 += x[i]*x[i];
            sum2 += Math.cos(2*Math.PI*x[i]);
        }
        result[0] = -20*Math.exp(-0.2*Math.sqrt(sum1/(double)dimension)) - Math.exp(sum2/(double)dimension) + 20 + Math.E;
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
	//return 1.8*Math.pow(10, -2); //FEP
	//return 18.96;
	return 0.002172668; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F10AckleyProblem(configuration, dimension);
    }

}
