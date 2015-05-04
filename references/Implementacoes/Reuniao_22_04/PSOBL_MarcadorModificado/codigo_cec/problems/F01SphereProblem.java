/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package clonalg_metamodel.problems;

import cec2008_competition.FastFractal;
import clonalg_metamodel.base.Problem;
import clonalg_metamodel.util.Configuration;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author hedersb
 */
public class F01SphereProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-100, 100};
    

    public F01SphereProblem(Configuration configuration, int dimension) {
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
            result[0] += x[i]*x[i];
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
        //return 150000;
	return 15000;
    }

    @Override
    public double getBestValue() {
	//return 5.7*Math.pow(10, -4); //FEP
	//return 0.00096;
	return 0.004073416; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F01SphereProblem(configuration, dimension);
    }

}
