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
public class F05RosenbrockProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-30, 30};

    public F05RosenbrockProblem(Configuration configuration, int dimension) {
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
        double aux1;
        double aux2;
        for (int i = 0; i < dimension-1; i++) {
            aux1 = x[i+1]-x[i]*x[i];
            aux2 = x[i]-1;
            result[0] += 100*aux1*aux1 + aux2*aux2;
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
        //return 2000000;
	//return 200000;
	return 40000; //usado no paper EI2010
    }

    @Override
    public double getBestValue() {
	//return 5.06; //avg value from FEP
	//return 27.6; //avg value from Cutello2005
	//return 31.07;
	return 27.32140; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F05RosenbrockProblem(configuration, dimension);
    }

}
