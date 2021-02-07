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

export class GaugeHalf extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
	}
	
	computeNeedleAngle(val) {
		let min_a = 180 - 80;
		let max_a = 180 + 80;
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
			<div className="GaugeHalf">
			 {this.renderNeedles()}
			</div>
		);
	}
}

GaugeHalf.defaultProps = {
  min: 0,
  max: 1,
};
