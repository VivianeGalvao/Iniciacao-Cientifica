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
public class F15KowalikProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-5, 5};

    public F15KowalikProblem(Configuration configuration) {
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
        double[] a = {0.1957, 0.1947, 0.1735, 0.1600, 0.0844, 0.0627, 0.0456, 0.0342, 0.0323, 0.0235, 0.0246};
	double[] b = {0.25, 0.5, 1, 2, 4, 6, 8, 10, 12, 14, 16};
	for (int i = 0; i < b.length; i++) {
	    b[i] = 1/b[i];
	}
	double aux;
	for (int i = 0; i < 11; i++) {
	    aux = a[i] - (x[0]*(b[i]*b[i]+b[i]*x[1]))/(b[i]*b[i] + b[i]*x[2] + x[3]);
	    result[0] += aux * aux;
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
        //return 400000;
	return 40000;
    }

    @Override
    public double getBestValue() {
	//return 5.0*Math.pow(10, -4); //FEP
	//return 0.0014;
	return 0.0003913586; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F15KowalikProblem(configuration);
    }

}
