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
public class F16SixHumpCamelBackProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-5, 5};

    public F16SixHumpCamelBackProblem(Configuration configuration) {
        this.configuration = configuration;
        this.dimension = 2;
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
        result[0] = 4*x[0]*x[0] - 2.1*x[0]*x[0]*x[0]*x[0] + (Math.pow(x[0], 6))/(3d) + x[0]*x[1] -4*x[1]*x[1] + 4*x[1]*x[1]*x[1]*x[1];
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
	//return -1.03; //FEP
	//return -1.0315;
	return -1.020457; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F16SixHumpCamelBackProblem(configuration);
    }

}
