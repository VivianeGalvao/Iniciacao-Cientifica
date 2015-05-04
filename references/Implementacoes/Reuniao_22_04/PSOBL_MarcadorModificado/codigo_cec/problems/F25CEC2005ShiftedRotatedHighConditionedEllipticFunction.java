/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package clonalg_metamodel.problems;

import cec2005_competition.F03_shifted_rotated_high_cond_elliptic;
import clonalg_metamodel.base.Problem;
import clonalg_metamodel.util.Configuration;

/**
 *
 * @author hedersb
 */
public class F25CEC2005ShiftedRotatedHighConditionedEllipticFunction extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-100, 100};
    private F03_shifted_rotated_high_cond_elliptic f;

    public F25CEC2005ShiftedRotatedHighConditionedEllipticFunction(Configuration configuration, int dimension) {
	this.dimension = dimension;
	this.configuration = configuration;
	this.f = new F03_shifted_rotated_high_cond_elliptic(dimension, -450);
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
	//x = new double[]{-32.2013, 64.9776, -38.3, -23.2582, -54.0088, 86.6286, -6.3009, -49.3644, 5.3499, 52.2418, -13.3643, 73.1263, -8.5691, -20.4915, -60.1487, 16.0884, -78.3319, 70.0387, -6.8521, -64.797, 65.4005, -26.0233, -33.8757, 51.5893, 27.6427, -69.4485, 25.5123, -59.0782, -66.5481, -51.2733};
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
	return new F25CEC2005ShiftedRotatedHighConditionedEllipticFunction(configuration, dimension);
    }

}
