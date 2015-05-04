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
public class RosenbrockProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;

    public RosenbrockProblem(Configuration configuration, int dimension) {
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
        for (int i = 0; i < x.length-1; i++) {
            aux1 = x[i+1]-x[i]*x[i];
            aux2 = 1-x[i];
            result[0] += 100*aux1*aux1 + aux2*aux2;
        }
        return result;
    }

    @Override
    public double[][] getBounds() {
        if (bound==null) {
            bound = new double[dimension][2];
            for (int i = 0; i < bound.length; i++) {
                bound[i][0] = -5.12;
                bound[i][1] = 5.12;
            }
        }
        return bound;
    }

    @Override
    public int getMaxNumberFitnessFuntionEvaluation() {
        return 10000;
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
