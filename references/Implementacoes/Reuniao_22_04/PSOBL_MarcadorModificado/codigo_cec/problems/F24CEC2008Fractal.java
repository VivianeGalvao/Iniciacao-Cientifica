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
public class F24CEC2008Fractal extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-1, 1};
    private FastFractal fastFractal;

    public F24CEC2008Fractal(Configuration configuration, int dimension) {
	this.dimension = dimension;
	this.configuration = configuration;
	try {
	    this.fastFractal = new FastFractal(3, 1, 1, dimension);
	} catch (Exception ex) {
	    Logger.getLogger(F01SphereProblem.class.getName()).log(Level.SEVERE, null, ex);
	}
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
        result[0] = this.fastFractal.evaluate(x);
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
	throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Problem clone() {
	return new F24CEC2008Fractal(this.configuration, this.dimension);
    }

}
