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
public class GriewankProblem extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;

    public GriewankProblem(Configuration configuration, int dimension) {
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
        double produto = 1;
        for (int i = 0; i < x.length; i++) {
            produto *= Math.cos(x[i])/Math.sqrt(i+1);
            result[0] += x[i]*x[i]/4000;
        }
        result[0] += 1 - produto;
        return result;
    }

    @Override
    public double[][] getBounds() {
        if (bound==null) {
            bound = new double[dimension][2];
            for (int i = 0; i < bound.length; i++) {
                bound[i][0] = -600;
                bound[i][1] = 600;
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
