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
public class F07QuarticnoiseProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-1.28, 1.28};

    public F07QuarticnoiseProblem(Configuration configuration, int dimension) {
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
        for (int i = 0; i < dimension; i++) {
            result[0] += (i+1)*x[i]*x[i]*x[i]*x[i];
        }
	result[0] += configuration.getRandom().nextDouble();
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
        //return 300000;
	return 30000;
    }

    @Override
    public double getBestValue() {
	//return 7.6*Math.pow(10, -3); //FEP
	//return 0.13;
	return 0.005583648; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F07QuarticnoiseProblem(configuration, dimension);
    }
    
}
