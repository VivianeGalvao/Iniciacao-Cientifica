/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package clonalg_metamodel.problems;

import cec2005_competition.F15_hybrid_composition_1;
import clonalg_metamodel.base.Problem;
import clonalg_metamodel.util.Configuration;

/**
 *
 * @author hedersb
 */
public class F27CEC2005HybridComposition1 extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-5, 5};
    private F15_hybrid_composition_1 f;

    public F27CEC2005HybridComposition1(Configuration configuration, int dimension) {
	this.dimension = dimension;
	this.configuration = configuration;
	this.f = new F15_hybrid_composition_1(dimension, 120);
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
        result[0] = this.f.f(x);
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
	throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Problem clone() {
	return new F27CEC2005HybridComposition1(configuration, dimension);
    }

}
