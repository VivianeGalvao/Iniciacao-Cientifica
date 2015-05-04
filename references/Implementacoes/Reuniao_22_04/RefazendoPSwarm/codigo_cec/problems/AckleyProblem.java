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
public class AckleyProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;

    public AckleyProblem(Configuration configuration, int dimension) {
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
        for (int i = 0; i < x.length; i++) {
            sum1 += x[i]*x[i];
            sum2 += Math.cos(2*Math.PI*x[i]);
        }
        result[0] = -20*Math.exp(-0.2*Math.sqrt(sum1/(double)x.length)) - Math.exp(sum2/(double)x.length) + 20 + Math.E;
        return result;
    }

    @Override
    public double[][] getBounds() {
        if (bound==null) {
            bound = new double[dimension][2];
            for (int i = 0; i < bound.length; i++) {
                bound[i][0] = -32.768;
                bound[i][1] = 32.768;
            }
        }
        return bound;
    }

    @Override
    public int getMaxNumberFitnessFuntionEvaluation() {
        return 3000;
    }

    @Override
    public double getBestValue() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Problem clone() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

}
