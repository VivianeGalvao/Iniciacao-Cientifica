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
public class F17BraninProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;

    public F17BraninProblem(Configuration configuration) {
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
	double aux = x[1] - (5.1*x[0]*x[0])/(4*Math.PI*Math.PI) + (5*x[0])/Math.PI - 6;
        result[0] = aux*aux + 10*(1-1/(8*Math.PI))*Math.cos(x[0]) + 10;
        return result;
    }

    @Override
    public double[][] getBounds() {
        if (bound==null) {
            bound = new double[dimension][2];
            bound[0][0] = -5;
	    bound[0][1] = 10;
	    bound[1][0] = 0;
	    bound[1][1] = 15;
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
	//return 0.398; //FEP
	//return 0.40061;
	return 0.4249669; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F17BraninProblem(configuration);
    }

}
