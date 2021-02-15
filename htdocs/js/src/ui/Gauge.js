 /*
  * This file is part of evQueue
  *
  * evQueue is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * evQueue is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with evQueue. If not, see <http://www.gnu.org/licenses/>.
  *
  * Author: Thibault Kummer
  */

'use strict';

export class Gauge extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
	}
	
	computeNeedleAngle(val) {
		let min_a = parseFloat(this.props.min_angle);
		let max_a = parseFloat(this.props.max_angle);
		return min_a + (max_a - min_a) * (val - this.props.min) / (this.props.max - this.props.min);
	}
	
	renderNeedles() {
		if(typeof(this.props.current)!='object')
		{
			let a = this.computeNeedleAngle(this.props.current);
			return (<div className="needle" style={{rotate: a+'deg'}}></div>);
		}
		else return this.props.current.map((cur, idx) => {
			let a = this.computeNeedleAngle(cur);
			return (<div key={idx} className="needle" style={{rotate: a+'deg'}}></div>);
		});
	}
	
	render() {
		
		return (
			<div className="Gauge">
				<div className="gauge">
					<div>
						{this.renderNeedles()}
					</div>
				</div>
				<div className="display">{this.props.display}</div>
			</div>
		);
	}
}

Gauge.defaultProps = {
	min: 0,
	max: 1,
	min_angle: -170,
	max_angle: 170
};
