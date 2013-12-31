/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "matrix.hpp"

namespace gamma {

template <typename T> struct mvp
{
	typedef mvp<T> self;
	typedef T scalar_type;
	typedef matrix3<T> matrix3_type;
	typedef matrix4<T> matrix4_type;

	const matrix4_type model;
	const matrix4_type view;
	const matrix4_type projection;

	const matrix4_type model_view;
	const matrix4_type model_view_projection;
	const matrix3_type normal;

	mvp(): model(1), view(1), projection(1),
		model_view(1),
		model_view_projection(1),
		normal(1) {}
	mvp(const matrix4_type& model, const matrix4_type& view, const matrix4_type& projection): model(model), view(view), projection(projection),
		model_view(view*model),
		model_view_projection(projection*model_view),
		normal(
			model_view.m00, model_view.m01, model_view.m02,
			model_view.m10, model_view.m11, model_view.m12,
			model_view.m20, model_view.m21, model_view.m22) {}

	mvp set            (const matrix4_type& m, const matrix4_type& v, const matrix4_type& p) const { return mvp(m, v, p); }
	mvp set_model      (const matrix4_type& m) const { return mvp(m, view, projection); }
	mvp set_view       (const matrix4_type& v) const { return mvp(model, v, projection); }
	mvp set_projection (const matrix4_type& p) const { return mvp(model, view, p); }

	mvp mul_model      (const matrix4_type& m) const { return mvp(model*m, view, projection); }
	mvp mul_view       (const matrix4_type& v) const { return mvp(model, view*v, projection); }
	mvp mul_projection (const matrix4_type& p) const { return mvp(model, view, projection*p); }

	mvp reset()            const { return mvp(); }
	mvp reset_model()      const { return mvp(matrix4_type(1), view, projection); }
	mvp reset_view()       const { return mvp(model, matrix4_type(1), projection); }
	mvp reset_projection() const { return mvp(model, view, matrix4_type(1)); }
};

typedef mvp<float>  mvpf;
typedef mvp<double> mvpd;

} // namespace gamma